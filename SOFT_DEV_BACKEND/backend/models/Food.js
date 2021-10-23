const mongoose = require('mongoose');
const { Schema } = mongoose;

const foodSchema = new Schema({
  name: {
    type: String,
    require: true,
  },
  image: {
    type: String, //path to image
  },
  owner: {
    type: mongoose.Types.ObjectId, // ถ้ามีแสดงว่ารูปนี้มาจากร้านค้า
  },
  calorie: {
    type: Number,
    require: true,
  },
  admin_create: {
    type: Boolean,
    default: false,
  },
});

mongoose.model('food', foodSchema);
