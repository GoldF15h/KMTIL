const mongoose = require('mongoose');
const { authorization } = require('../middleware/Authorization');
const Report = mongoose.model('report');

module.exports = (app) => {
  app.get('/reports', authorization, async (req, res) => {
    // console.log('in get-report');
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const report = await Report.find(
        {},
        {
          store_id: 1,
          detail: 1,
          owner: 1,
          is_modify: 1,
        },
      );

      message = {
        report,
      };
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    }

    res.status(200).send({ status: statusMessage, message });
    // console.log('end get-report');
  });

  app.put('/reports', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const _store_id = req.body.store_id || 'empty';
      const _detail = req.body.detail || 'empty';
      const _owner = req.body.owner || 'empty';
      const _is_modify = req.body.is_modify || 0;

      if (req.body.id) {
        const report = await Report.findOneAndUpdate(
          {
            _id: req.body.id,
          },
          {
            store_id: _store_id,
            detail: _detail,
            owner: _owner,
            is_modify: 1,
          },
          {
            new: true,
            projection: {
              store_id: 1,
              detail: 1,
              owner: 1,
              is_modify: 1,
            },
          },
        );

        if (report) {
          // console.log(report);
          message = {
            report,
          };
        } else {
          statusCode = 404;
          statusMessage = 'error';
          message = 'report not fond';
        }
      }
    } catch (err) {
      console.log(err.message);
      statusCode = 400;
      statusMessage = 'error';
      message = 'bad req';
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.post('/reports', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const report = new Report({
        store_id: req.body.store_id,
        detail: req.body.detail,
        owner: req.body.owner,
        is_modify: false,
      });
      await report.save();
      message = 'report create success';
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    }

    res.status(statusCode).send({ status: statusMessage, message });
  });
};
