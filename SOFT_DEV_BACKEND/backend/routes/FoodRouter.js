const mongoose = require('mongoose');
const { supervisorAuthorization } = require('../middleware/Authorization');
const uploadFileMiddleware = require('../middleware/FoodUpload');
const FoodUpload = require('../middleware/FoodUpload');
const Food = mongoose.model('food');

module.exports = (app) => {
  app.get('/food/:id', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const food = await Food.findOne(
        {
          _id: req.params.id,
        },
        {
          _id: 1,
          name: 1,
          image: 1,
          owner: 1,
          calorie: 1,
        },
      );
      message = {
        food,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.get('/foodstore/', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const food = await Food.find(
        {
          owner: req.user._id,
        },
        {
          _id: 1,
          name: 1,
          image: 1,
          owner: 1,
          calorie: 1,
        },
      );

      message = {
        food,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.get('/food', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const food = await Food.find(
        {},
        {
          _id: 1,
          name: 1,
          image: 1,
          owner: 1,
          calorie: 1,
        },
      );

      message = {
        food,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.put('/food', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      await FoodUpload(req, res);
      console.log(req.body);
      const food = await Food.findOne({
        _id: req.body.id,
      });
      console.log(food);

      food.set(req.body);
      await food.save();

      // message = food;
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

  app.post('/food', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'post success';
    let message = null;
    // อย่าลืม userid
    try {
      await FoodUpload(req, res);
      // console.log(req.body);
      let adminCreate = false;
      if (req.user.role === 'Admin') {
        adminCreate = true;
      }
      if (req.body.url_image) {
        const food = new Food({
          name: req.body.name,
          image: req.body.url_image,
          owner: req.user._id,
          calorie: req.body.calorie,
          admin_create: adminCreate,
        });

        await food.save();

        statusCode = 200;
        statusMessage = 'success';
        message = 'food created success';
      } else {
        statusCode = 400;
        statusMessage = 'fail';
        message = 'empty image!';
      }
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
};
