const mongoose = require('mongoose');
const { disableRegister } = require('../config/Keys');
const User = mongoose.model('user');
const upload = require('../middleware/Upload');
const { authorization } = require('../middleware/Authorization');

module.exports = (app) => {
  app.get('/users/profile', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      let usernameFind = '';
      let userProjection = null;
      let isowner = false;

      if (
        req.query.username === 'me' ||
        req.query.username === req.user.username
      ) {
        // query with /profile/me => /profile/owner_username
        isowner = true;

        usernameFind = req.user.username;
        userProjection = {
          _id: 0,
          username: 1,
          display_name: 1,
          weight: 1,
          height: 1,
          birthday: 1,
          gender: 1,
          job: 1,
          url_profile: 1,
        };
      } else {
        usernameFind = req.query.username;
        userProjection = {
          _id: 0,
          username: 1,
          display_name: 1,
          url_profile: 1,
        };
      }

      const user = await User.findOne(
        {
          username: usernameFind,
        },
        userProjection,
      );

      console.log(user);
      // console.log(user);
      // Todo เชค Token แล้วส่งให้เฉพาะ Data ส่วนตัวเท่านั้น <-- maybe ทำแล้วมั้ง

      if (user) {
        statusCode = 200;
        statusMessage = 'success';
        message = { user, isowner };
      } else {
        statusCode = 404;
        statusMessage = 'error';
        message = 'User not found';
      }
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

  app.put('/users/profile', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      // console.log(req.body);
      await upload(req, res);
      // console.log(req.body);
      const user = await User.findOne({
        username: req.user.username,
      });

      console.log(user);
      // delete key: username
      delete req.body.username;

      // set with req.body
      user.set(req.body);
      await user.save();

      statusCode = 200;
      statusMessage = 'success';
      message = 'Update user profile successfully';
    } catch (err) {
      if (err.code == 'LIMIT_FILE_SIZE') {
        statusCode = 400;
        statusMessage = 'error';
        message = 'File size cannot be larger than 2MB!';
      } else {
        statusCode = 400;
        statusMessage = 'error';
        message = err.message;
        // console.log(err.message);
      }
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.post('/users/register', async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    if (disableRegister) {
      message = 'register not allow';
      res.status(statusCode).send({
        status: statusMessage,
        message,
      });
    }
    try {
      console.log('req body:', req.body);

      const checkUsername = await User.findOne({
        username: req.body.username,
      });

      if (checkUsername) {
        statusCode = 400;
        statusMessage = 'error';
        message = 'username exists already!';
      } else {
        const user = new User({
          username: req.body.username,
          email: req.body.email,
          password: req.body.password,
          display_name: req.body.display_name,
          timestamp: new Date(),
        });
        // console.log(user);
        user.token = user.genToken(48);
        await user.save();

        statusCode = 200;
        statusMessage = 'success';
        message = { msg: 'user created successfully', token: user.token };
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

  app.post('/users/login', async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      // console.log(req.body);
      const user = await User.findOne({ username: req.body.username });
      if (user) {
        const passwordCheck = await user.comparePassword(req.body.password);
        if (passwordCheck === true) {
          user.token = user.genToken(48);
          await user.save();

          statusCode = 200;
          statusMessage = 'success';
          message = {
            token: user.token,
          };
        } else {
          statusCode = 200;
          statusMessage = 'error';
          message = 'username or password is incorrect';
        }
      } else {
        statusCode = 200;
        statusMessage = 'error';
        message = 'username or password is incorrect';
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

  app.post('/users/logout', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      // console.log(req.headers.authorization);
      const user = await User.findOne({
        token: req.headers.authorization,
      });
      if (user) {
        user.token = '';
        await user.save();

        statusCode = 200;
        statusMessage = 'success';
        message = 'logout successfully';
      } else {
        statusCode = 401;
        statusMessage = 'error';
        message = 'token not found';
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
