var axios = require('axios');
var FormData = require('form-data');
var fs = require('fs');

const photo_path = process.cwd() + '/images/';
const token =
  'e46a74f0f601d3a8527ec012cc58ba4452a9680dd549c16df2e57838bb655bc4ffa5414dd6f9eff7e76aee706a1847ae';

function dump(config) {
  axios(config)
    .then(function (response) {
      // console.log(JSON.stringify(response.data));
      console.log('success');
    })
    .catch(function (error) {
      console.log(error.message);
    });
}

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement1' + '.png'));
data.append('name', "it' just the begining");
data.append('description', 'login for 1 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement2' + '.png'));
data.append('name', 'on step further');
data.append('description', 'login for 10 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement3' + '.png'));
data.append('name', 'the run begin');
data.append('description', 'run for 10 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement4' + '.png'));
data.append('name', 'running is fun');
data.append('description', 'run for 50 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement5' + '.png'));
data.append('name', "running isn't that hard");
data.append('description', 'run for 100 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement6' + '.png'));
data.append('name', 'try no to drown');
data.append('description', 'swim for 1 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement7' + '.png'));
data.append('name', 'feel like i got a fin');
data.append('description', 'swim for 10 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement8' + '.png'));
data.append('name', 'i can breath under water');
data.append('description', 'swim for 20 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append('image', fs.createReadStream(photo_path + 'achievement9' + '.png'));
data.append('name', 'i am a friend of shark');
data.append('description', 'swim for 50 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append(
  'image',
  fs.createReadStream(photo_path + 'achievement10' + '.jpg'),
);
data.append('name', 'aquaman');
data.append('description', 'swim for 100 times');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append(
  'image',
  fs.createReadStream(photo_path + 'achievement11' + '.png'),
);
data.append('name', 'my first album');
data.append('description', 'took 10 pictures');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);

var data = new FormData();
data.append(
  'image',
  fs.createReadStream(photo_path + 'achievement12' + '.png'),
);
data.append('name', 'camera man');
data.append('description', 'took 100 pictures');
data.append('score', '10');

var config = {
  method: 'post',
  url: 'http://localhost:5000/api/v1/achievement',
  headers: {
    Authorization: token,
    ...data.getHeaders(),
  },
  data: data,
};

dump(config);
