const mongoose = require('mongoose');
const {
  authorization,
  supervisorAuthorization,
} = require('../middleware/Authorization');
const { calculateBMR, calculateRecCal } = require('../middleware/Calculate');
const {
  FoodPhotoUpload,
  unlinkAsync,
} = require('../middleware/FoodPhotoUpload');
const Food = mongoose.model('food');
const Reader = require('../middleware/QRcodeReader');
const FoodPhoto = mongoose.model('foodphoto');
const FolderPath = process.cwd() + '/resources/static/assets/uploads/';

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}

module.exports = (app) => {
  app.get('/foodphoto/:id', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const food_photo = await FoodPhoto.findOne(
        {
          _id: req.params.id,
        },
        {
          _id: 1,
          food_id: 1,
          owner: 1,
          create_at: 1,
          image: 1,
        },
      ).populate({
        path: 'food_id',
        model: 'food',
        select: {
          name: 1,
          calorie: 1,
          _id: 0,
        },
      });

      message = {
        food_photo,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    // ใส่ findOne

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.get('/foodphoto/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const foodphoto = await FoodPhoto.find(
        { owner: req.user._id },
        {
          _id: 1,
          food_id: 1,
          // owner: 1,
          create_at: 1,
          image: 1,
        },
      ).populate({
        path: 'food_id',
        model: 'food',
        select: {
          calorie: 1,
          _id: 0,
        },
      });

      const BMR = calculateBMR(req.user);
      const recCal = calculateRecCal(req.user, BMR);
      const zeroPad = (num, places) => String(num).padStart(places, '0');
      console.log(BMR, recCal);
      const sumCalorie = {};
      const groups = foodphoto.reduce((groups, e) => {
        // console.log(groups, e);
        let date =
          zeroPad(e.create_at.getDate(), 2) +
          '-' +
          zeroPad(e.create_at.getMonth() + 1, 2) +
          '-' +
          zeroPad(e.create_at.getFullYear(), 4);
        if (!groups[date]) {
          groups[date] = [];
          sumCalorie[date] = 0;
          // groups[date].push({ test: 'test' });
          // console.log('create new list', date);
        }
        groups[date].push(e);
        sumCalorie[date] += parseInt(e.food_id.calorie) || 0;
        return groups;
      }, {});

      // console.log(sumCalorie);

      // console.log(groups);

      // Edit: to add it in the array format instead
      const numRange = 200;
      let type = 'normal';
      const groupFoodPhoto = Object.keys(groups).map((date) => {
        console.log(
          sumCalorie[date] - numRange,
          sumCalorie[date] + numRange,
          sumCalorie[date],
        );
        if (sumCalorie[date] < recCal - numRange) type = 'less';
        else if (sumCalorie[date] > recCal + numRange) type = 'more';
        // console.log(groups[date]);
        return {
          date,
          sum_calorie: sumCalorie[date],
          type,
          food_photo: groups[date],
        };
      });

      // console.log(groupFoodPhoto);

      message = {
        group_food_photo: groupFoodPhoto,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    // ใส่ findOne

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.put('/foodphoto/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const _food_id = req.body.food_id || 'empty';
      const _owner = req.body.owner || 'empty';
      const _image = req.body.image || 'empty';

      if (req.body.id) {
        const foodphoto = await FoodPhoto.findOneAndUpdate(
          {
            _id: req.body.id,
          },
          {
            food_id: _food_id,
            owner: _owner,
            image: _image,
          },
          {
            new: true,
            projection: {
              food_id: 1,
              owner: 1,
              image: 1,
            },
          },
        );

        if (foodphoto) {
          message = {
            foodphoto,
          };
        } else {
          statusCode = 404;
          statusMessage = 'error';
          message = 'food photo not fond';
        }
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad req';
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  // create food photo! for user
  app.post('/foodphoto/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'post success';
    let message = null;
    try {
      await FoodPhotoUpload(req, res);
      // console.log(req.user._id);
      // await unlinkAsync(FolderPath + req.body.url_image); // for debug only
      // console.log(req.body);
      const foodphoto = new FoodPhoto({
        food_id: req.body.food_id,
        owner: req.user._id,
        image: req.body.url_image,
        create_at: new Date(),
      });
      // console.log(foodphoto);
      await foodphoto.save();
      statusCode = 200;
      statusMessage = 'success';
      message = 'food photo created success';
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  // preprocess route
  app.post('/foodphotopreprocess/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'post success';
    let message = null;
    try {
      await FoodPhotoUpload(req, res);
      // console.log(req.body, req.user);
      if (req.body.url_image) {
        const result = await Reader(req.body.url_image);
        let image_process = {};
        let process_with_ml = false;
        let food_list = [];
        let found = false;
        if (result) {
          if (result.startsWith('food_store_')) {
            // find food
            const food = await Food.findOne(
              {
                _id: result.split('_')[2],
              },
              {
                _id: 1,
                name: 1,
                // image: 1,
                // owner: 1,
                calorie: 1,
              },
            );
            if (food) {
              // console.log(food);
              image_process = { name: food.name, calorie: food.calorie };
              found = true;
            }
          }
        }
        if (!found) {
          // find all image create with admin
          const foodList = await Food.find(
            {
              admin_create: true,
            },
            { _id: 1, name: 1, calorie: 1 },
          );
          // console.log(foods);
          food_list = foodList;
          image_process = foodList[getRandomInt(foodList.length)]; // will be ML
          // console.log(image_process);
          process_with_ml = true;
        }

        statusCode = 200;
        statusMessage = 'success';
        message = {
          image_process,
          process_with_ml,
          food_list,
        };
      } else {
        statusCode = 400;
        statusMessage = 'fail';
        message = 'empty image!';
      }
    } catch (error) {
      // console.log(error.message);
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    } finally {
      await unlinkAsync(FolderPath + req.body.url_image); // remove after processing
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });
};
