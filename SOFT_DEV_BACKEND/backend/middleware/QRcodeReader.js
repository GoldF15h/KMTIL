//Importing jimp module
var Jimp = require('jimp');
var fs = require('fs');
var QrCode = require('qrcode-reader');

const Reader = async (filename) => {
  return new Promise((resolve, reject) => {
    var buffer = fs.readFileSync(
      process.cwd() + '/resources/static/assets/uploads/' + filename,
    );

    Jimp.read(buffer, function (err, image) {
      if (err) {
        console.error(err);
        // TODO handle error
      }
      var qr = new QrCode();
      qr.callback = function (err, value) {
        if (err) {
          // console.error(err);
          resolve(null);
          // TODO handle error
        } else {
          resolve(value.result);
          // console.log(value.result);
        }
      };
      qr.decode(image.bitmap);
    });
  });
};

module.exports = Reader;
