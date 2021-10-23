const mongoose = require('mongoose');
const { supervisorAuthorization } = require('../../middleware/Authorization');

// User it mean Supervisor
const User = mongoose.model('supervisor');

module.exports = (app) => {
  // get profile
  app.get('/supervisor/profile', supervisorAuthorization, async (req, res) => {
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
          role: 1,
        };
      } else {
        usernameFind = req.query.username;
        userProjection = {
          _id: 0,
          username: 1,
          display_name: 1,
          role: 1,
        };
      }

      const user = await User.findOne(
        {
          username: usernameFind,
        },
        userProjection,
      );
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

  // register ต้องถูกสร้างโดย Supervisor ที่เป็น admin เท่านั้น
  app.post('/supervisor/register', async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
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
          password: req.body.password,
          display_name: req.body.display_name,
          role: req.body.role,
          create_at: new Date(),
        });

        // save user
        await user.save();

        statusCode = 200;
        statusMessage = 'success';
        message = 'user created successfully';
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  app.post('/supervisor/login', async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      // console.log(req.body);
      const userProjection = {
        _id: 0,
        username: 1,
        display_name: 1,
        role: 1,
      };

      const user = await User.findOne({
        username: req.body.username,
      });

      if (user) {
        const passwordCheck = await user.comparePassword(req.body.password);
        if (passwordCheck === true) {
          user.token = user.genToken(48);
          await user.save();

          statusCode = 200;
          statusMessage = 'success';
          message = {
            token: user.token,
            user_data: {
              username: user.username,
              role: user.role,
              display_name: user.display_name,
            },
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
      console.log(error.message);
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.post('/supervisor/logout', supervisorAuthorization, async (req, res) => {
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
