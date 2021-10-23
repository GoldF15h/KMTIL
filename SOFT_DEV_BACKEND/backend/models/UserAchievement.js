const mongoose = require('mongoose');
const { Schema } = mongoose;

const userAchievementSchema = new Schema({
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  target: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
});

mongoose.model('userachievement', userAchievementSchema);
