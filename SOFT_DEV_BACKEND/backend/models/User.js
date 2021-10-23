const mongoose = require('mongoose');
const { Schema } = mongoose;
const bcrypt = require('bcrypt');
const SALT_WORK_FACTOR = 10;

// import job from settings
const { job } = require('./settings/Job');

const userSchema = new Schema({
  username: {
    type: String,
    required: true,
    index: {
      unique: true,
    },
  },
  email: {
    type: String,
    required: true,
  },
  password: {
    type: String,
    required: true,
  },
  display_name: {
    type: String,
    required: true,
  },
  birthday: {
    type: String,
  },
  create_at: {
    type: Date,
    default: new Date(),
  },
  weight: {
    type: Number,
  },
  height: {
    type: Number,
  },
  url_profile: {
    type: String,
  },
  token: {
    type: String,
  },
  job: {
    type: String,
    enum: job,
    default: job[0],
  },
  gender: {
    type: String,
    enum: ['เพศชาย', 'เพศหญิง'],
  },
});

userSchema.pre('save', function (next) {
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

userSchema.methods.comparePassword = function (candidatePassword) {
  try {
    return bcrypt.compare(candidatePassword, this.password);
  } catch (error) {
    return false;
  }
};

userSchema.methods.genToken = function (length) {
  const token = require('crypto').randomBytes(length).toString('hex');
  return token;
};

mongoose.model('user', userSchema);
