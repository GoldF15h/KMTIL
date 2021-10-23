const mongoose = require('mongoose');
const Stat = mongoose.model('stat');
const userstatus = require('../middleware/UserStatus');
// const test = require('../test/DumpDatabase');
const { authorization } = require('../middleware/Authorization');

module.exports = (app) => {
  app.get('/test', authorization, async (req, res) => {
    console.log('\n\n\n***************************************');
    await userstatus.photo(req);
    // await userstatus.exercise(req, { swim: 20 });
    // await userstatus.checkChallenge(req);
    console.log('return from middleware ->', await userstatus.getStat(req));
    console.log('***************************************\n\n\n');
    res.status(200).send({
      status: 'ok',
    });
  });
};
