const mongoose = require('mongoose');
const User = mongoose.model('supervisor');
const Store = mongoose.model('store');
const {
  authorization,
  supervisorAuthorization,
} = require('../middleware/Authorization');

module.exports = (app) => {
  app.get('/store/:id', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const store = await Store.find(
        {
          _id: req.params.id,
        },
        {
          _id: 1,
          name: 1,
          owner: 1,
          create_at: 1,
        },
      );

      message = {
        store,
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

  app.get('/store', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const store = await Store.find(
        {},
        {
          _id: 1,
          name: 1,
          owner: 1,
          create_at: 1,
        },
      ).populate({
        path: 'owner',
        model: 'supervisor',
        select: 'username display_name role',
      });

      message = {
        store,
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

  app.put('/store', supervisorAuthorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      console.log(req.user);
      const _name = req.body.name || 'empty';
      const _display_name = req.body.display_name || 'empty';
      const _username = req.body.username || 'empty';
      const _password = req.body.password || 'empty';

      const user = await User.findOneAndUpdate(
        {
          _id: req.user._id,
        },
        {
          username: _username,
          password: _password,
          is_modify: 1,
        },
        {
          new: true,
          projection: {
            username: 1,
            password: 1,
            is_modify: 1,
          },
        },
      );
      // console.log('hello');

      if (!user) {
        statusCode = 404;
        statusMessage = 'error';
        message = 'user not fond';
      }
      // console.log('*****************\n', req.user._id);
      const store = await Store.findOneAndUpdate(
        {
          owner: req.user._id,
        },
        {
          name: _name,
          display_name: _display_name,
          is_modify: 1,
        },
        {
          new: true,
          projection: {
            name: 1,
            display_name: 1,
            is_modify: 1,
          },
        },
      );

      if (!store) {
        statusCode = 404;
        statusMessage = 'error';
        message = 'store not fond';
      }
    } catch (err) {
      // console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.post('/store', supervisorAuthorization, async (req, res) => {
    // for create
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    // อย่าลืม userid
    try {
      console.log('req body', req.body, 'end');

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
          create_at: new Date(),
        });

        // save user
        await user.save();

        const store = new Store({
          name: req.body.name,
          owner: user._id,
          create_at: new Date(),
        });
        //   console.log(achievemant);
        await store.save();

        statusCode = 200;
        statusMessage = 'success';
        message = 'store created success';
      }
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
      console.log(error.message);
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });
};
