const mongoose = require('mongoose');

const Challenge = mongoose.model('challenge');
const { authorization } = require('../middleware/Authorization');

module.exports = (app) => {
  // get UserAchievement by id
  app.get('/challenge/:type', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    // console.log(req.query);
    const skip = Number.parseInt(req.query.skip) || 0;
    const limit = Number.parseInt(req.query.limit) || 20;
    const requsetTpye = req.params.type;
    try {
      if (requsetTpye === 'income') {
        // console.log('in in_come', req.params);
        const challenge = await Challenge.find(
          {
            target: req.user.id,
          },
          {
            owner: 1,
            target: 1,
            achievement: 1,
            is_accept: 1,
            is_decline: 1,
            is_success: 1,
            create_at: 1,
          },
          { skip: skip, limit: limit },
        ).populate({
          path: 'owner',
          model: 'user',
          select: 'username url_profile display_name',
        });
        // console.log(req.params.tpye);
        message = {
          challenge,
        };
      } else if (requsetTpye === 'outcome') {
        const challenge = await Challenge.find(
          {
            owner: req.user.id,
          },
          {
            owner: 1,
            target: 1,
            achievement: 1,
            is_accept: 1,
            is_decline: 1,
            is_success: 1,
            create_at: 1,
          },
          { skip: skip, limit: limit },
        ).populate({
          path: 'target',
          model: 'user',
          select: 'username url_profile display_name',
        });

        message = {
          challenge,
        };
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

  // get all UserAchievement
  app.get('/challenge', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    console.log('hello');
    try {
      const challenge = await Challenge.find(
        {},
        {
          owner: 1,
          target: 1,
          achievement: 1,
          is_accept: 1,
          is_decline: 1,
          is_success: 1,
          create_at: 1,
        },
      );

      message = {
        challenge,
      };
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  // update UserAchievement ต้องมีมั้ย??
  app.put('/challenge', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    5;

    try {
      const _achievement = req.body.achievement || 'empty';
      const _is_accept = req.body.is_accept || 0;
      const _is_decline = req.body.is_decline || 0;
      const _is_success = req.body.is_success || 0;

      if (req.body.id) {
        const challenge = await Challenge.findOneAndUpdate(
          {
            _id: req.body.id,
          },
          {
            achievement: _achievement,
            is_accept: _is_accept,
            is_decline: _is_decline,
            is_success: _is_decline,
          },
          {
            new: true,
            projection: {
              achievement: 1,
              is_accept: 1,
              is_decline: 1,
              is_success: 1,
            },
          },
        );

        if (challenge) {
          message = {
            challenge,
          };
        } else {
          statusCode = 404;
          statusMessage = 'error';
          message = 'challenge not found';
        }
      }
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = 'bed request';
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  // create UserAchievement
  app.post('/challenge', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      console.log(req.body);
      const challenge = new Challenge({
        owner: req.body.owner,
        target: req.body.target,
        achievement: req.body.achievement,
        is_accept: false,
        is_decline: false,
        is_success: false,
        create_at: new Date(),
      });

      await challenge.save();

      message = 'user challenge create success';
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
