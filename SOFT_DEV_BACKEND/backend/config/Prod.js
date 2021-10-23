// prod.js - production keys here!!
module.exports = {
  mongoURL: process.env.MONGO_URI,
  disableRegister: process.env.DISABLE_REGISTER,
  origin: process.env.ORIGIN,
};
