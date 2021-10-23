const mongoose = require('mongoose');
const { Schema } = mongoose;

const statSchema = new Schema({
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
    index: {
      unique: true,
    },
  },
  login_number: {
    type: Number,
    default: 0,
  },
  photo_number: {
    type: Number,
    default: 0,
  },
  exercise_numbers: {
    run: {
      amount: {
        type: Number,
        default: 0,
      },
      time: {
        type: Number,
        default: 0,
      },
      cal: {
        type: Number,
        default: 0,
      },
    },
    walk: {
      amount: {
        type: Number,
        default: 0,
      },
      time: {
        type: Number,
        default: 0,
      },
      cal: {
        type: Number,
        default: 0,
      },
    },
    swim: {
      amount: {
        type: Number,
        default: 0,
      },
      time: {
        type: Number,
        default: 0,
      },
      cal: {
        type: Number,
        default: 0,
      },
    },
  },
});

mongoose.model('stat', statSchema);
