const util = require('util');
const multer = require('multer');
const maxSize = 2 * 1024 * 1024;

const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, process.cwd() + '/resources/static/assets/uploads/');
  },
  filename: (req, file, cb) => {
    // console.log(req.body);
    // const extension = file.originalname.split('.').pop();
    // console.log(req);
    const newName =
      req.user.username + '_achievement_' + new Date().getTime() + '.' + 'png';
    //+ new Date().getTime()
    req.body.url_image = newName;
    // console.log(newName);
    cb(null, newName);
  },
});

const uploadFile = multer({
  storage: storage,
  limits: { fileSize: maxSize },
  fileFilter: (req, file, cb) => {
    if (
      file.mimetype == 'image/png' ||
      file.mimetype == 'image/jpg' ||
      file.mimetype == 'image/jpeg'
    ) {
      cb(null, true);
    } else {
      cb(null, false);
      return cb(new Error('Only .png, .jpg and .jpeg format allowed!'));
    }
  },
}).single('image');

let uploadFileMiddleware = util.promisify(uploadFile);

module.exports = uploadFileMiddleware;
