const mongoose = require('mongoose');
const { Schema } = mongoose;

const challengeSchema = new Schema({
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  target: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  achievement: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  is_accept: {
    type: Boolean,
  },
  is_decline: {
    type: Boolean,
  },
  is_success: {
    type: Boolean,
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
});

mongoose.model('challenge', challengeSchema);
