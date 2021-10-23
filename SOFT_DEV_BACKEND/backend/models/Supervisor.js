const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const SALT_WORK_FACTOR = 10;
const { Schema } = mongoose;

const supervisorSchema = new Schema({
  username: {
    type: String,
    require: true,
    index: {
      unique: true,
    },
  },
  password: {
    type: String,
  },
  display_name: {
    type: String,
  },
  role: {
    type: String,
    require: true,
    enum: ['Admin', 'Store'],
    default: 'Store',
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
  token: {
    type: String,
  },
});

supervisorSchema.pre('save', function (next) {
  var user = this;

  // only hash the password if it has been modified (or is new)
  if (!user.isModified('password')) return next();

  // generate a salt
  bcrypt.genSalt(SALT_WORK_FACTOR, function (err, salt) {
    if (err) return next(err);

    // hash the password using our new salt
    bcrypt.hash(user.password, salt, function (err, hash) {
      if (err) return next(err);
      // override the cleartext password with the hashed one
      user.password = hash;
      next();
    });
  });
});

supervisorSchema.methods.comparePassword = function (candidatePassword) {
  try {
    return bcrypt.compare(candidatePassword, this.password);
  } catch (error) {
    return false;
  }
};

supervisorSchema.methods.genToken = function (length) {
  const token = require('crypto').randomBytes(length).toString('hex');
  return token;
};

mongoose.model('supervisor', supervisorSchema);
