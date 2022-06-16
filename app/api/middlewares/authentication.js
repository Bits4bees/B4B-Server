// //models import
import User from "../models/user.js";

const jwt = require('jsonwebtoken'); 

let checkAuth = (req, res, next) => {

    let token = req.get('token');

    jwt.verify(token, process.env.AUTH_TOKEN_PASSWORD, async (err, decoded) => {
    // jwt.verify(token, "securePasswordHere", (err, decoded) => {

        if (err){
            console.log("AUTHENTICATION ERROR ");
            return res.status(401).json({
              status: "error",
              error: err  
            });
        }

        // verify the user exist
        let _id = decoded.userData._id;
        let email = decoded.userData.email;

        if ( !await User.findOne({ _id: _id, email: email }) ){
            console.log("AUTHENTICATION ERROR ");
            return res.status(401).json({
              status: "error",
              error: err  
            });
        }

        req.userData = decoded.userData;

        console.log("AUTHENTICATION : SUCCESS");

        next();

    });

}

module.exports = {checkAuth}

// //models import
// import User from "../models/user.js";

// //POST -> req.body
// //GET -> req.query

// //******************
// //**** A P I *******
// //******************

// //LOGIN
// router.post("/login", async (req, res) => {
//   try {
//     const email = req.body.email;
//     const password = req.body.password;

//     var user = await User.findOne({ email: email });