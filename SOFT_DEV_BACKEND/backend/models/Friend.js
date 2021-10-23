const mongoose = require('mongoose');
const { Schema } = mongoose;

const friendSchema = new Schema({
  owner: {
    type: Schema.Types.ObjectId,
    ref: 'user',
    require: true,
  },
  target: {
    type: Schema.Types.ObjectId,
    ref: 'user',
    require: true,
  },
  is_accept: {
    type: Boolean,
    default: false,
  },
  is_decline: {
    type: Boolean,
    default: false,
  },
  is_delete: {
    type: Boolean,
    default: false,
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
  lase_modify: {
    type: Date,
    default: new Date(),
  },
});

friendSchema.index({ owner: 1, target: 1 }, { unique: true });

mongoose.model('friend', friendSchema);
