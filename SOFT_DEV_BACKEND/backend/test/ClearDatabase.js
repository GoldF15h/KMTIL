const mongoose = require('mongoose');
const keys = require('../config/Keys');

mongoose.connect(
  keys.mongoURL,
  {
    useNewUrlParser: true,
    useUnifiedTopology: true,
  },
  function (err) {
    if (err) {
      console.log(`can't connect to database`);
    } else {
      console.log(`connect to database successfully`);
      clearDatabase();
    }
  },
);

clearDatabase = async () => {
  try {
    const collections = await mongoose.connection.db.collections();
    for (let collection of collections) {
      await collection.deleteMany({});
    }
    console.log('drop all table successfully.');
  } catch (err) {}
  mongoose.connection.close(() => {
    console.info('closed');
  });
};
