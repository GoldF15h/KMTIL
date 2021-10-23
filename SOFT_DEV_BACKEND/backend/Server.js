require('dotenv').config({ path: __dirname + '/.env' });
const express = require('express');
const mongoose = require('mongoose');
const keys = require('./config/Keys');
const bodyParser = require('body-parser');
const mongoSanitize = require('express-mongo-sanitize');
const cors = require('cors');
const morgan = require('morgan');
const fs = require('fs');
const photo_dir = './resources/static/assets/uploads';
const mkdirp = require('mkdirp');

const corsOptions = {
  origin: keys.origin,
  optionsSuccessStatus: 200, // some legacy browsers (IE11, various SmartTVs) choke on 204
  methods: 'GET,PUT,POST',
};

mongoose.connect(
  keys.mongoURL,
  {
    useNewUrlParser: true,
    useUnifiedTopology: true,
    useCreateIndex: true,
    useFindAndModify: false,
    // auth: {
    // 	authSource: 'admin',
    // },
    // user: 'admin',
    // pass: 'password',
  },

  function (err) {
    if (err) {
      console.log('🚀 ~ file: server.js ~ line 22 ~ err', err);
    } else {
      console.log('Successfully connected to MongoDB');
    }
  },
);

const app = express();

app.use(morgan('dev'));
app.use(cors(corsOptions));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(mongoSanitize()); // noSQL injection protection!
app.use('/api/v1', require('./Routes'));

const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
  folderManager();
  console.log(`App listening at http://localhost:${PORT}`);
});

const folderManager = () => {
  if (fs.existsSync(photo_dir)) {
    console.log('photo floder is exsit');
  } else {
    console.log('(not) error : photo floder is not exsit!!');
    try {
      fs.mkdir(photo_dir, { recursive: true }, (err) => {
        console.log('Photo directory is created.');
      });
    } catch (err) {
      console.log('fail to create floder \n' + err.message);
    }
  }
};
