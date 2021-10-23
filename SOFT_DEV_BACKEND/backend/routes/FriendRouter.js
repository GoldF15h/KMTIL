const mongoose = require('mongoose');
const { authorization } = require('../middleware/Authorization');
const Friend = mongoose.model('friend');
const User = mongoose.model('user');

module.exports = (app) => {
  // query income and outcome
  app.get('/friends/:type', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    const skip = Number.parseInt(req.query.skip) || 0;
    const limit = Number.parseInt(req.query.limit) || 20;

    try {
      if (req.params.type === 'income') {
        // console.log(req.user._id);
        console.log('query income');

        const friendRequestList = await Friend.find(
          {
            is_accept: false,
            is_decline: false,
            is_delete: false,
            target: req.user._id,
          },
          {
            _id: 0,
            is_accept: 1,
            is_delete: 1,
            is_decline: 1,
            timestamp: 1,
            owner: 1,
          },
          {
            skip: skip,
            limit: limit,
          },
        ).populate({
          path: 'owner',
          model: 'user',
          select: 'username url_profile display_name',
        });

        message = { users: friendRequestList, next: skip + limit };
      } else if (req.params.type === 'outcome') {
        console.log('query outcome');

        const friendRequestList = await Friend.find(
          {
            is_accept: false,
            is_decline: false,
            is_delete: false,
            owner: req.user._id,
          },
          {
            _id: 0,
            is_accept: 1,
            is_delete: 1,
            is_decline: 1,
            timestamp: 1,
            target: 1,
          },
          {
            skip: skip,
            limit: limit,
          },
        ).populate({
          path: 'target',
          model: 'user',
          select: 'username url_profile display_name',
        });

        message = { users: friendRequestList, next: skip + limit };
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  // with username
  app.get('/friend', authorization, async (req, res) => {
    console.log(req.query.target);
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    try {
      const targetUser = await User.findOne(
        { username: req.query.target },
        {
          username: 1,
          url_profile: 1,
          display_name: 1,
        },
      );
      if (targetUser) {
        const res = await Friend.findOne({
          $or: [
            { owner: req.user._id, target: targetUser._id },
            { target: req.user._id, owner: targetUser._id },
          ],
        })
          .populate({
            path: 'target',
            model: 'user',
            select: 'username url_profile display_name',
          })
          .populate({
            path: 'owner',
            model: 'user',
            select: 'username url_profile display_name',
          });

        if (res) {
          const isOwner = String(req.user._id) === String(res.owner._id);
          statusCode = 200;
          statusMessage = 'success';

          let modifiedUser;
          if (isOwner) {
            modifiedUser = {
              user: res.target,
            };
          } else {
            modifiedUser = {
              user: res.owner,
            };
          }

          message = {
            is_accept: res.is_accept,
            is_delete: res.is_delete,
            is_decline: res.is_decline,
            _id: res._id,
            user: modifiedUser.user,
          };
        } else {
          statusCode = 200;
          statusMessage = 'success';
          message = {
            type: 'new',
            user: targetUser,
          };
        }
      } else {
        statusCode = 404;
        statusMessage = 'error';
        message = 'User not found.';
      }
    } catch (err) {
      console.log(err.message);

      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }
    res.status(statusCode).send({ status: statusMessage, message });
  });

  // only accept status
  app.get('/friends/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    const skip = Number.parseInt(req.query.skip) || 0;
    const limit = Number.parseInt(req.query.limit) || 20;

    try {
      const friendList = await Friend.find(
        {
          is_accept: true,
          is_decline: false,
          is_delete: false,
          $or: [{ owner: req.user._id }, { target: req.user._id }],
        },
        {
          _id: 0,
          is_accept: 1,
          is_delete: 1,
          is_decline: 1,
          timestamp: 1,
          target: 1,
          owner: 1,
        },
        {
          skip: skip,
          limit: limit,
        },
      )
        .populate({
          path: 'target',
          model: 'user',
          select: 'username url_profile display_name',
        })
        .populate({
          path: 'owner',
          model: 'user',
          select: 'username url_profile display_name',
        });

      // console.log(friendList);
      let cleanList = [];

      friendList.forEach((element) => {
        if (String(element.target._id) !== String(req.user._id)) {
          cleanList.push({ ...element.target._doc, score: 1000 });
          // console.log(String(element.target._id), String(req.user._id));
        }
        if (String(element.owner._id) !== String(req.user._id)) {
          cleanList.push({ ...element.owner._doc, score: 1111 });
          // console.log(String(element.owner._id), String(req.user._id));
        }
      });

      cleanList = [...new Set(cleanList)];

      // console.log(cleanList);

      message = { users: cleanList, next: skip + limit };
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  // Create friend request
  app.post('/friends/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;
    console.log(req.body);

    try {
      const targetUser = await User.findOne({ username: req.body.target });

      if (targetUser && targetUser.username !== req.user.username) {
        const findRequest = await Friend.findOne(
          {
            $or: [
              {
                owner: req.user._id,
                target: targetUser._id,
              },
              {
                target: req.user._id,
                owner: targetUser._id,
              },
            ],
          },
          {
            _id: 0,
            target: 1,
            owner: 1,
            is_accept: 1,
            is_decline: 1,
            is_delete: 1,
          },
        )
          .populate({
            path: 'target',
            model: 'user',
            select: 'username url_profile display_name',
          })
          .populate({
            path: 'owner',
            model: 'user',
            select: 'username url_profile display_name',
          });
        if (findRequest) {
          // console.log(req.user._id, findRequest.owner._id);
          const isOwner =
            String(req.user._id) === String(findRequest.owner._id);
          statusCode = 200;
          statusMessage = 'success';

          let modifiedUser;
          if (isOwner) {
            modifiedUser = {
              user: findRequest.target,
            };
          } else {
            modifiedUser = {
              user: findRequest.owner,
            };
          }

          message = {
            type: 'duplicate request',
            is_owner: isOwner,
            user: modifiedUser.user,
          };
        } else {
          const friend = new Friend({
            owner: req.user._id,
            target: targetUser._id,
          });

          try {
            const res = await friend.save();
            statusCode = 200;
            statusMessage = 'success';
            message = {
              msg: 'created a new request successfully',
              request: {
                _id: res._id,
                target: res.target,
                is_accept: res.is_accept,
              },
            };
          } catch (error) {
            console.log(error.message);
            statusCode = 400;
            statusMessage = 'error';
            message = 'bad friend request || duplicate request';
          }
        }
      } else {
        statusCode = 404;
        statusMessage = 'error';
        message = 'target username was wrong!';
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });

  // update friend record
  app.put('/friends/', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const targetUser = await User.findOne({ username: req.body.target });
      const _accept = req.body.is_accept || false;
      const _decline = req.body.is_decline || false;
      const _delete = req.body.is_delete || false;

      const friend = await Friend.findOneAndUpdate(
        {
          $or: [
            { owner: req.user._id, target: targetUser._id },
            { target: targetUser._id, owner: req.user._id },
          ],
        },
        {
          is_accept: _accept,
          is_decline: _decline,
          is_delete: _delete,
          last_modify: new Date(),
        },
        {
          new: true,
          projection: {
            is_accept: 1,
            is_decline: 1,
            is_delete: 1,
            target: 1,
            owner: 1,
          },
        },
      );
      message = {
        after_modify: friend,
      };
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad request';
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });
};
