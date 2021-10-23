const mongoose = require('mongoose');
const { Schema } = mongoose;

const exerciseSchema = new Schema({
  name: {
    type: String,
    require: true,
    index: {
      unique: true,
    },
  },
  description: {
    type: String,
  },
  cal_p_h: {
    type: Number,
    require: true,
  },
});

mongoose.model('exercise', exerciseSchema);
