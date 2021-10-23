const mongoose = require('mongoose');
const { Schema } = mongoose;

const achivementSchema = new Schema({
  name: {
    type: String,
  },
  description: {
    type: String,
  },
  icon: {
    type: String, // path to image
  },
  score: {
    type: Number,
  },
});

mongoose.model('achievement', achivementSchema);
