const axios = require('axios');
var FormData = require('form-data');
var fs = require('fs');

const numberOfUser = 5;

let allUser = [];

function padLeadingZeros(num, size) {
  var s = num + '';
  while (s.length < size) s = '0' + s;
  return s;
}

const createUser = async () => {
  for (let i = 0; i < numberOfUser; i++) {
    const _number = padLeadingZeros(i, String(numberOfUser).length);
    var dataObject = {
      username: `tester${_number}`,
      email: `tester${_number}@gmail.com`,
      password: `password${_number}`,
      displayname: `whoami_${_number}`,
    };

    const jsonString = JSON.stringify(dataObject);
    var config = {
      method: 'post',
      url: 'http://localhost:5000/api/v1//users/register',
      headers: {
        'Content-Type': 'application/json',
      },
      data: jsonString,
    };
    let res;
    try {
      res = await axios(config);
      if (res.data.status === 'success') {
        console.log(`Create user ${dataObject.username} successfully`);
        const token = await login(dataObject.username, dataObject.password);
        if (token) {
          console.log(
            `Login user ${dataObject.username} successfully, token ${token}`,
          );
          await updateProfile(token);
          allUser.push({ username: `tester${_number}`, token: token });
        } else {
          console.log(`Login user ${dataObject.username} fail`);
        }
      } else {
        console.log(`Create user ${dataObject.username} fail`);
      }
    } catch (err) {
      console.log(err.message);
      // break;
    }
  }
  for (const x of allUser) {
    for (const y of allUser) {
      addFriend(x.token, y.username);
      console.log(`${x.username} add ${y.username}`);
    }
    // addFriend
  }
};

const login = async (username, password) => {
  var data = JSON.stringify({ username: username, password: password });
  // console.log(data);
  var config = {
    method: 'post',
    url: 'http://localhost:5000/api/v1//users/login',
    headers: {
      'Content-Type': 'application/json',
    },
    data: data,
  };
  const res = await axios(config);
  // console.log(res.data);
  if (res.data.status === 'success') {
    return res.data.message.token;
  } else {
    return null;
  }
};

const updateProfile = async (token) => {
  var data = new FormData();
  data.append(
    'file',
    fs.createReadStream(process.cwd() + '/test/images/image.jpg'),
  );
  data.append('job', randJob());
  data.append('weight', randNumRange(30, 100));
  data.append('height', randNumRange(100, 100));
  data.append('gender', randGender());
  data.append('birthday', '2000-09-28');
  console.log(data.getHeaders());
  var config = {
    method: 'put',
    url: 'http://localhost:5000/api/v1/users/profile',
    headers: {
      authorization: token,
      ...data.getHeaders(),
    },
    data: data,
  };

  const res = await axios(config);
  if (res.data.status === 'success') {
    console.log('Updated');
  } else {
    console.log('Update Fail');
  }
};

function randNumRange(min, max) {
  return min + Math.floor(Math.random() * Math.floor(max));
}

const randGender = () => {
  const listGender = ['B', 'G'];
  const ranGender = Math.floor(Math.random() * listGender.length);
  return listGender[ranGender];
};

const randJob = () => {
  const listJob = ['Programmer', 'Student'];
  const ranJob = Math.floor(Math.random() * listJob.length);
  return listJob[ranJob];
};

const addFriend = async (token, target) => {
  var config = {
    method: 'post',
    url: 'http://localhost:5000/api/v1/friends',
    headers: {
      Authorization: token,
      'Content-Type': 'application/json',
    },
    data: JSON.stringify({ target: target }),
  };
  try {
    const res = await axios(config);
    // console.log(res.data.message);
    if (res.data.status === 'success') {
      return res.data.message.requestid;
    }
  } catch (err) {}
};

createUser();
// console.log('hello');
