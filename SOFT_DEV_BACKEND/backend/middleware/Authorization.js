const mongoose = require('mongoose');
const User = mongoose.model('user');
const Supervisor = mongoose.model('supervisor');

async function authorization(req, res, next) {
  const token = req.header('authorization') || '';
  const userProjection = {
    _id: 1,
    username: 1,
    displayname: 1,
    weight: 1,
    height: 1,
    birthday: 1,
    gender: 1,
    job: 1,
  };
  const user = await User.findOne(
    {
      token,
    },
    userProjection,
  );
  if (user) {
    // console.log(user);
    req.user = user;
    next();
  } else {
    res.status(401).send({ status: 'error', message: 'Unauthorized' });
  }
}

// dashboard authorization
async function supervisorAuthorization(req, res, next) {
  const token = req.header('authorization') || '';
  const userProjection = {
    _id: 1,
    username: 1,
    display_name: 1,
    role: 1,
    create_at: 1,
  };
  const user = await Supervisor.findOne(
    {
      token,
    },
    userProjection,
  );
  if (user) {
    // console.log(user);
    req.user = user;
    next();
  } else {
    res.status(401).send({ status: 'error', message: 'Unauthorized' });
  }
}

module.exports = {
  authorization,
  supervisorAuthorization,
};
