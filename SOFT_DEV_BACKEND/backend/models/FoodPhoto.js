const mongoose = require('mongoose');
const { Schema } = mongoose;

const foodPhotoSchema = new Schema({
  food_id: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
  image: {
    type: String, // path to image
    require: true,
  },
});

mongoose.model('foodphoto', foodPhotoSchema);
