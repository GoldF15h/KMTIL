// keys.js - figure out what set of credentials to return
if (process.env.NODE_ENV === 'production') {
  // we are in production - return the prod set of keys
  console.log('env: Production!');
  module.exports = require('./Prod');
} else {
  // we are in development - return the dev keys!!!
  console.log('env: Dev!');
  module.exports = require('./Dev');
}
