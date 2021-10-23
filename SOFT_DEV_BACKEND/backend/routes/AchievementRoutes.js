const mongoose = require('mongoose');
const { authorization } = require('../middleware/Authorization');

const Achievemant = mongoose.model('achievement');
const AchievementUpload = require('../middleware/AchievementPhotoUpload');
// ดู middle ware ว่าต้องใช้ตัวไหนบ้าง

module.exports = (app) => {
  app.get('/achievement/:id', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const achievemant = await Achievemant.find(
        {
          _id: req.params.id,
        },
        {
          _id: 1,
          name: 1,
          description: 1,
          icon: 1,
          score: 1,
        },
      );

      message = {
        achievemant,
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

  app.get('/achievement', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const achievemant = await Achievemant.find(
        {},
        {
          _id: 1,
          name: 1,
          description: 1,
          icon: 1,
          score: 1,
        },
      );

      message = {
        achievemant,
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

  app.put('/achievement', authorization, async (req, res) => {
    // for update แต่จำเป็นต้องมีมั้ย ????
    let statusCode = 200;
    let statusMessage = 'put success';
    let message = null;

    try {
      const _name = req.body.name || 'empty';
      const _description = req.body.description || 'empty';
      const _icon = req.body.icon || 'empty';
      const _score = req.body.score || 0;

      if (req.body.id) {
        const achievemant = await Achievemant.findOneAndUpdate(
          {
            _id: req.body.id,
          },
          {
            name: _name,
            destcription: _description,
            icon: _icon,
            score: _score,
          },
          {
            new: true,
            projection: {
              name: 1,
              description: 1,
              icon: 1,
              score: 1,
            },
          },
        );

        if (achievemant) {
          message = {
            achievemant,
          };
        } else {
          statusCode = 404;
          statusMessage = 'error';
          message = 'achievement not fond';
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

  app.post('/achievement', authorization, async (req, res) => {
    // for create
    let statusCode = 200;
    let statusMessage = 'post success';
    let message = null;
    // อย่าลืม userid
    try {
      // console.log('req body', req.body, 'end');
      await AchievementUpload(req, res);
      // console.log('req body', req.body, 'end');
      const achievemant = new Achievemant({
        name: req.body.name,
        description: req.body.description,
        icon: req.body.url_image,
        score: req.body.score,
      });
      // console.log(achievemant);
      await achievemant.save();

      statusCode = 200;
      statusMessage = 'success';
      message = 'achievement created success';
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
