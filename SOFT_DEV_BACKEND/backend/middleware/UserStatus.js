const mongoose = require('mongoose');
const Stat = mongoose.model('stat');
const Achievemant = mongoose.model('achievement');
const userAchievement = mongoose.model('userachievement');
const Challenge = mongoose.model('challenge');
// const all_achievement = null;

async function getStat(req) {
  try {
    const stat = await Stat.findOne(
      {
        owner: req.user._id,
      },
      {
        owner: 1,
        login_number: 1,
        photo_number: 1,
        exercise_numbers: 1,
      },
    );

    if (stat) {
      //   console.log('stat found');
      return stat;
    } else {
      //   console.log('create new stat');
      const new_stat = new Stat({
        owner: req.user._id,
      });
      // console.log(new_stat);
      await new_stat.save();
      return new_stat;
    }
  } catch (err) {
    console.log('error', err.message);
  }
}

async function login(req) {
  try {
    const stat = await getStat(req);

    const _login_number = stat.login_number + 1;
    stat.login_number = _login_number;
    chechLoginAchievement(req, stat);
    stat.save();
  } catch (err) {
    console.log('error', err.message);
  }
}

async function photo(req) {
  try {
    console.log('in photo');
    const stat = await getStat(req);
    const _photo_number = stat.photo_number + 10;
    stat.photo_number = _photo_number;
    chechPhotoAchievement(req, stat);
    stat.save();
  } catch (err) {
    console.log('error', err.message);
  }
}

async function exercise(
  req,
  {
    run,
    run_time,
    run_cal,
    walk,
    walk_time,
    walk_cal,
    swim,
    swim_time,
    swim_cal,
  },
) {
  try {
    const stat = await getStat(req);

    if (run) {
      const _run = (stat.exercise_numbers.run.amount || 0) + run;
      stat.exercise_numbers.run.amount = _run;
    }
    if (run_time) {
      const _run_time = (stat.exercise_numbers.run.time || 0) + run_time;
      stat.exercise_numbers.run.time = _run_time;
    }
    if (run_cal) {
      const _run_cal = (stat.exercise_numbers.run.cal || 0) + run_cal;
      stat.exercise_numbers.run.cal = _run_cal;
    }
    if (walk) {
      const _walk = (stat.exercise_numbers.walk.amount || 0) + walk;
      stat.exercise_numbers.walk.amount = _walk;
    }
    if (walk_time) {
      const _walk_cal = (stat.exercise_numbers.walk.time || 0) + walk_time;
      stat.exercise_numbers.walk.time = _walk_time;
    }
    if (walk_cal) {
      const _walk_cal = (stat.exercise_numbers.walk.cal || 0) + walk_cal;
      stat.exercise_numbers.walk.cal = _walk_cal;
    }
    if (swim) {
      const _swim = (stat.exercise_numbers.swim.amount || 0) + swim;
      stat.exercise_numbers.swim.amount = _swim;
    }
    if (swim_time) {
      const _swim_time = (stat.exercise_numbers.swim.time || 0) + swim_time;
      stat.exercise_numbers.swim.time = _swim_time;
    }
    if (swim_cal) {
      const _swim_cal = (stat.exercise_numbers.swim.cal || 0) + swim_cal;
      stat.exercise_numbers.swim.cal = _swim_cal;
    }
    // console.log('before check');
    await checkExerciseAchievement(req, stat);
    await stat.save();
  } catch (err) {
    console.log('error', err.message);
  }
}

async function chechLoginAchievement(req, stat) {
  const all_achievement = await Achievemant.find(
    {},
    {
      _id: 1,
      name: 1,
      description: 1,
      icon: 1,
      score: 1,
    },
  );
  const all_userachievement = await userAchievement.find(
    {
      owner: req.user._id,
    },
    {
      _id: 1,
      owner: 1,
      target: 1,
    },
  );

  const achievementLen = all_achievement.length;
  const userAchievementLen = all_userachievement.length;
  var currentAchievement, currentUserAchievement;

  for (
    currentAchievement = 0;
    currentAchievement < achievementLen;
    currentAchievement++
  ) {
    const findAchievement = all_achievement[currentAchievement]._id;
    currentAchievementArr = all_achievement[
      currentAchievement
    ].description.split(' ');
    const _tpye = currentAchievementArr[0] || ' ';
    const _value = parseInt(currentAchievementArr[2] || '0');
    var _json = stat.login_number;
    if (_tpye != 'login') {
      // console.log('skip!');
      continue;
    }
    // console.log("it's login");

    var isPass = false;
    if (_json >= _value) {
      isPass = true;
    }

    if (isPass) {
      var isExist = false;
      for (
        currentUserAchievement = 0;
        currentUserAchievement < userAchievementLen;
        currentUserAchievement++
      ) {
        if (
          all_userachievement[currentUserAchievement].target.toString() ==
          findAchievement.toString()
        ) {
          isExist = true;
          break;
        }
      }
      if (!isExist) {
        const userachievement = new userAchievement({
          owner: req.user._id,
          target: findAchievement,
          create_at: new Date(),
        });
        await userachievement.save();
      }
    }
  }
}

async function chechPhotoAchievement(req, stat) {
  const all_achievement = await Achievemant.find(
    {},
    {
      _id: 1,
      name: 1,
      description: 1,
      icon: 1,
      score: 1,
    },
  );
  const all_userachievement = await userAchievement.find(
    {
      owner: req.user._id,
    },
    {
      _id: 1,
      owner: 1,
      target: 1,
    },
  );

  const achievementLen = all_achievement.length;
  const userAchievementLen = all_userachievement.length;
  var currentAchievement, currentUserAchievement;

  for (
    currentAchievement = 0;
    currentAchievement < achievementLen;
    currentAchievement++
  ) {
    const findAchievement = all_achievement[currentAchievement]._id;
    currentAchievementArr = all_achievement[
      currentAchievement
    ].description.split(' ');
    const _tpye = currentAchievementArr[2] || ' ';
    const _value = parseInt(currentAchievementArr[1] || '0');
    var _json = stat.photo_number;
    if (_tpye != 'pictures') {
      // console.log('skip!');
      continue;
    }
    // console.log("it's photo");

    var isPass = false;
    if (_json >= _value) {
      isPass = true;
    }

    if (isPass) {
      var isExist = false;
      for (
        currentUserAchievement = 0;
        currentUserAchievement < userAchievementLen;
        currentUserAchievement++
      ) {
        if (
          all_userachievement[currentUserAchievement].target.toString() ==
          findAchievement.toString()
        ) {
          isExist = true;
          break;
        }
      }
      if (!isExist) {
        const userachievement = new userAchievement({
          owner: req.user._id,
          target: findAchievement,
          create_at: new Date(),
        });
        await userachievement.save();
      }
    }
  }
}

async function checkExerciseAchievement(req, stat) {
  // console.log('\n\n\n\nin checkExerciseAchievement\n');
  // เดี๋ยวเปลี่ยนเป็นการ load จากตอน run ครั้งแรกตอนนี้เอาแบบนี้ไปก่อน
  const all_achievement = await Achievemant.find(
    {},
    {
      _id: 1,
      name: 1,
      description: 1,
      icon: 1,
      score: 1,
    },
  );
  // console.log(
  //   '\n\n\n all achievement',
  //   all_achievement,
  //   '\n\n\n all achievement\n\n\n',
  // );
  const all_userachievement = await userAchievement.find(
    {
      owner: req.user._id,
    },
    {
      _id: 1,
      owner: 1,
      target: 1,
    },
  );
  // console.log(
  //   '\n\n\n all achievement',
  //   all_userachievement,
  //   '\n\n\n all achievement\n\n\n',
  // );

  const achievementLen = all_achievement.length;
  const userAchievementLen = all_userachievement.length;
  var currentAchievement, currentUserAchievement;
  // console.log("len :",len);
  for (
    currentAchievement = 0;
    currentAchievement < achievementLen;
    currentAchievement++
  ) {
    // แบ่ง achievement จาก description
    const findAchievement = all_achievement[currentAchievement]._id;
    currentAchievementArr = all_achievement[
      currentAchievement
    ].description.split(' ');
    const _tpye = currentAchievementArr[0] || ' ';
    const _value = parseInt(currentAchievementArr[2] || '0');
    const _unit = currentAchievementArr[3] || ' ';
    var _json = {};
    switch (
      _tpye // ถ้าเป็น achievement แบบไหนก็ให้เอา stat การออกกำลังกาย นั้นออกมา
    ) {
      case 'run':
        _json = stat.exercise_numbers.run;
        break;
      case 'walk':
        _json = stat.exercise_numbers.walk;
      case 'swim':
        _json = stat.exercise_numbers.swim;
        break;
    }
    // console.log(stat.exercise_numbers.run);
    // console.log(findAchievement, _tpye, _value, _unit, _json);

    // เช็คว่า achiement นี้ผ่านมั้ยแล้วเข้า for
    var isPass = false;
    switch (
      _unit // ถ้าเป็นหน่วยไหน ก็ให้เอาหน่วยนั้นของการออกกำลังกายใน _json ออกมาเช็คว่าผ่านมั้ย ถ้าไม่ผ่านให้ conitnue เช็คอันต่อไปเลย
    ) {
      case 'times':
        if (_json.amount >= _value) {
          isPass = true;
        }
        break;
      case 'minute':
        if (_json.time >= _value) {
          isPass = true;
        }
        break;
      case 'calories':
        if (_json.cal >= _value) {
          isPass = true;
        }
        break;
    }
    // console.log(isPass);
    if (isPass) {
      // ถ้ามาถึงบรรทัดนี้แปลว่าสามารถรับ currentAchievement ได้
      // เข้า loop สำหรับเช็คว่ามี achievement นี้หรือไม่
      // console.log('achievement pass !! finding in userAchievement');
      var isExist = false;
      for (
        currentUserAchievement = 0;
        currentUserAchievement < userAchievementLen;
        currentUserAchievement++
      ) {
        if (
          all_userachievement[currentUserAchievement].target.toString() ==
          findAchievement.toString()
        ) {
          // ถ้าเจอ achievement
          // console.log('achievement found');
          isExist = true;
          break;
        }
      }
      if (!isExist) {
        // ถ้าไม่เจอ achievement
        const userachievement = new userAchievement({
          owner: req.user._id,
          target: findAchievement,
          create_at: new Date(),
        });
        // console.log('new user achievement!!', userachievement);
        await userachievement.save();
      }
    }
  }
}

async function checkChallenge(req) {
  const all_userachievement = await userAchievement.find(
    {
      owner: req.user._id,
    },
    {
      _id: 1,
      owner: 1,
      target: 1,
    },
  );

  const challenge = await Challenge.find(
    {
      target: req.user._id,
    },
    {
      owner: 1,
      target: 1,
      achievement: 1,
      is_accept: 1,
      is_decline: 1,
      is_success: 1,
      create_at: 1,
    },
  );

  // console.log(challenge);

  var challengeLen = challenge.length;
  var currentChallenge = 0;
  for (
    currentChallenge = 0;
    currentChallenge < challengeLen;
    currentChallenge++
  ) {
    if (challenge[currentChallenge].is_decline == true) {
      continue;
    }
    if (challenge[currentChallenge].is_success == true) {
      continue;
    }
    if (challenge[currentChallenge].is_accept == false) {
      continue;
    }
    const userAchievementLen = all_userachievement.length;
    var currentUserAchievement;
    for (
      currentUserAchievement = 0;
      currentUserAchievement < userAchievementLen;
      currentUserAchievement++
    ) {
      // console.log(
      //   all_userachievement[currentUserAchievement].target.toString(),
      //   challenge[currentChallenge].achievement.toString(),
      // );
      if (
        all_userachievement[currentUserAchievement].target.toString() ===
        challenge[currentChallenge].achievement.toString()
      ) {
        console.log('challenge success');
        challenge[currentChallenge].is_success = true;
        await challenge[currentChallenge].save();
      }
    }
  }
}

module.exports = {
  login,
  photo,
  exercise,
  getStat,
  checkChallenge,
};
