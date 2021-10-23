const mongoose = require('mongoose');
const { Schema } = mongoose;

const storeSchema = new Schema({
  name: {
    type: String,
    require: true,
  },
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
    index: {
      unique: true,
    },
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
});

mongoose.model('store', storeSchema);
