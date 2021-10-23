const mongoose = require('mongoose');
const { authorization } = require('../middleware/Authorization');

const userAchievement = mongoose.model('userachievement');
// ดู middle ware ว่าต้องใช้ตัวไหนบ้าง

module.exports = (app) => {
  app.get('/userachievement/:id', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const userachievemant = await userAchievement.find(
        {
          owner: req.params.id,
        },
        {
          _id: 1,
          owner: 1,
          target: 1,
          create_at: 1,
        },
      );

      message = {
        userachievemant,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.get('/userachievement', authorization, async (req, res) => {
    let statusCode = 200;
    let statusMessage = 'success';
    let message = null;

    try {
      const userachievemant = await userAchievement.find(
        {},
        {
          _id: 1,
          owner: 1,
          target: 1,
          create_at: 1,
        },
      );

      message = {
        userachievemant,
      };
    } catch (err) {
      statusCode = 400;
      statusMessage = 'error';
      message = err.message;
    }

    // ใส่ findOne

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });

  app.post('/userachievement', authorization, async (req, res) => {
    // for create
    let statusCode = 200;
    let statusMessage = 'post success';
    let message = null;
    // อย่าลืม userid
    try {
      console.log('req body', req.body, 'end');
      const userachievemant = new userAchievement({
        owner: req.body.owner,
        target: req.body.target,
        create_at: new Date(),
      });
      console.log(userachievemant);
      await userachievemant.save();

      statusCode = 200;
      statusMessage = 'success';
      message = 'userachievemant created success';
    } catch (error) {
      statusCode = 400;
      statusMessage = 'error';
      message = error.message;
    }

    res.status(statusCode).send({
      status: statusMessage,
      message,
    });
  });
};
