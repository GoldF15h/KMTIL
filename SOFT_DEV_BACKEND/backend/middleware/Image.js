const fs = require('fs');
const middlewareImage = (req, res) => {
  // console.log('./resources/static/assets/uploads/' + req.params.name);
  try {
    const data = fs.readFileSync(
      // process.cwd() +
      './resources/static/assets/uploads/' + req.params.name,
    );
    var base64 = Buffer.from(data).toString('base64');
    base64 = 'data:image/png;base64,' + base64;
    // res.sendFile(
    //   process.cwd() +
    //   '/resources/static/assets/uploads/' +
    //   req.params.name
    //   );
    res.status(200).send({ status: 'success', message: base64 });
  } catch (error) {
    console.log(error);
    res.status(404).send({ status: 'error', message: 'Not found' });
  }
  // res.send('yayyy');
};

module.exports = middlewareImage;
