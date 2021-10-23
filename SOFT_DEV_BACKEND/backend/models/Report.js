const mongoose = require('mongoose');
const { Schema } = mongoose;

const reportSchema = new Schema({
  store_id: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  detail: {
    type: String,
  },
  owner: {
    type: mongoose.Types.ObjectId,
    require: true,
  },
  is_modify: {
    type: Boolean,
  },
});

mongoose.model('report', reportSchema);
