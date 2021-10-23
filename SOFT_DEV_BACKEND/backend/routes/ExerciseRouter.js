const mongoose = require('mongoose');
const { authorization } = require('../middleware/Authorization');
const Exercise = mongoose.model('exercise');
const UserExercise = mongoose.model('userexercise');

module.exports = (app) => {
  // get with id
  // return only one
  app.get('/exercise/:id', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
      const exercise = await Exercise.findOne(
        {
          _id: req.params.id,
        },
        {
          _id: 0,
          name: 1,
          description: 1,
          cal_p_h: 1,
        },
      );

      if (exercise) {
        message = {
          exercise,
        };
      } else {
        statusCode = 404;
        statusMessage = 'error';
        message = 'exercise not fond';
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  // get all
  // return list of exercise
  app.get('/exercise', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const exercises = await Exercise.find(
        {},
        {
          _id: 1,
          name: 1,
          description: 1,
          cal_p_h: 1,
        },
      );

      message = {
        exercises,
      };
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  // create new exercise
  // this route for admin create master exercise
  app.post('/exercise', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
      const exercise = new Exercise({
        name: req.body.name,
        description: req.body.description,
        cal_p_h: req.body.cal_p_h,
      });

      const _res = await exercise.save();
      statusCode = 200;
      statusMessage = 'success';
      message = {
        msg: 'created a new exercise successfully',
        id: _res._id,
      };
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }
    res.status(statusCode).send({ status: statusMessage, message });
  });

  // update new exercise
  // this route for admin update master exercise
  app.put('/exercise', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
      const _name = req.body.name || 'empty';
      const _description = req.body.description || 'empty';
      const _cal_p_h = req.body.cal_p_h || 0;

      if (req.body.id) {
        const exercise = await Exercise.findOneAndUpdate(
          {
            _id: req.body.id,
          },
          { name: _name, description: _description, cal_p_h: _cal_p_h },
          {
            new: true,
            projection: {
              name: 1,
              description: 1,
              cal_p_h: 1,
            },
          },
        );

        if (exercise) {
          message = {
            exercise,
          };
        } else {
          statusCode = 404;
          statusMessage = 'error';
          message = 'exercise not fond';
        }
      } else {
        statusCode = 400;
        statusMessage = 'error';
        message = 'request object id';
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }
    res.status(statusCode).send({ status: statusMessage, message });
  });

  // create new user exercise
  // this route for user create new exercise
  app.post('/exercise/user', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const exercise = await Exercise.findOne({
        _id: req.body.exercise_id,
      });
      if (exercise) {
        //console.log('req.user => ', req.user);
        let date = new Date();
        let dayNumber = parseInt(req.body.start_at);
        date.setSeconds(Math.floor(dayNumber % 100));
        dayNumber = dayNumber / 100;
        date.setMinutes(Math.floor(dayNumber % 100));
        dayNumber = dayNumber / 100;
        date.setHours(Math.floor(dayNumber % 100));
        dayNumber = dayNumber / 100;
        date.setFullYear(Math.floor(dayNumber % 10000));
        dayNumber = dayNumber / 10000;
        date.setMonth(Math.floor(dayNumber % 100) - 1);
        dayNumber = dayNumber / 100;
        date.setDate(Math.floor(dayNumber));
        console.log(date.getTime());
        console.log(date.toString());
        const userExercise = new UserExercise({
          exercise_id: req.body.exercise_id,
          time: req.body.time,
          start_at: date,
          owner: req.user._id,
        });
        const _res = await userExercise.save();

        if (_res)
          message = {
            msg: 'created a new exercise successfully',
            userExercise,
          };
      } else {
        statusCode = 404;
        statusMessage = 'error';
        message = 'exercise not fond';
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }
    res.status(statusCode).send({ status: statusMessage, message });
  });

  // get user exercise with id
  // this route for user
  app.get('/exercises/user/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
      const exercises = await UserExercise.find(
        {
          owner: req.user._id,
        },
        {
          _id: 1,
          exercise_id: 1,
          time: 1,
        },
      ).populate({
        path: 'exercise_id',
        model: 'exercise',
        select: 'name description cal_p_h',
      });

      message = {
        exercises: exercises || [],
      };
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });
};
