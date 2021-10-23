const Job = require('../models/settings/Job');
/*
  ref: https://en.wikipedia.org/wiki/Harris–Benedict_equation
  men:    BMR = 66.5 + ( 13.75 × weight in kg ) + ( 5.003 × height in cm ) – ( 6.755 × age in years )
  women: 	BMR = 655 + ( 9.563 × weight in kg ) + ( 1.850 × height in cm ) – ( 4.676 × age in years )
  */
const calculateBMR = (user) => {
  let BMR = 0;
  const age = getYears(user.birthday);
  if (user.gender === 'เพศชาย') {
    BMR =
      66.5 +
      13.75 * (user.weight || 0) +
      5.003 * (user.height || 0) -
      6.755 * (age || 0);
  } else if (user.gender === 'เพศหญิง') {
    BMR =
      655 +
      9.563 * (user.weight || 0) +
      1.85 * (user.height || 0) -
      4.676 * (age || 0);
  } else {
    // ยังไม่ได้กำหนดเพศ
    return null;
  }
  return BMR;
};

const calculateRecCal = (user, bmr) => {
  const index = Job.job.indexOf(user.job);
  return bmr * Job.multiply[index];
};

module.exports = {
  calculateBMR,
  calculateRecCal,
};

function getYears(birthday) {
  const n = Date.now();
  const d = new Date(birthday);
  const delta = n - d;
  return Math.floor(delta / 1000 / 60 / 60 / 24 / 365);
}
