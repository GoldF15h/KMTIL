const mongoose = require('mongoose');
const { Schema } = mongoose;

const userExerciseSchema = new Schema({
  exercise_id: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  time: {
    type: Number,
  },
  start_at: {
    type: Date,
  },
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
});

mongoose.model('userexercise', userExerciseSchema);
