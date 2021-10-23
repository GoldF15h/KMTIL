const app = require('express');
const router = app.Router();

// load modules
require('./models/User');
require('./models/Friend');
require('./models/Achievement');
require('./models/Challenge');
require('./models/Exercise');
require('./models/Food');
require('./models/FoodPhoto');
require('./models/Report');
require('./models/Store');
require('./models/Supervisor');
require('./models/UserAchievement');
require('./models/UserExercise');
require('./models/stat');

const {
  authorization,
  supervisorAuthorization,
} = require('./middleware/Authorization');
router.get('/images/:name', require('./middleware/Image'));
require('./routes/UserRoutes')(router);
require('./routes/FriendRouter')(router);
require('./routes/AchievementRoutes')(router);
require('./routes/ExerciseRouter')(router);
require('./routes/ChallengeRouter')(router);
require('./routes/ReportRouter')(router);
require('./routes/StoreRouter')(router);
require('./routes/FoodRouter')(router);
require('./routes/FoodPhotoRouter')(router);
require('./routes/test')(router);
require('./routes/UserAchievementRoute')(router);
// // dashboard
require('./routes/dashboard/UserRoute')(router);

module.exports = router;
