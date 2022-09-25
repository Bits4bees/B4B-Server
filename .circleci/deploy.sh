mkdir /home/circleci/.aws
 touch /home/circleci/.aws/config
 chmod 600 /home/circleci/.aws/config
 echo "[profile user]" > /home/circleci/.aws/config
 echo "aws_access_key_id=$AWS_ACCESS_KEY_ID" >> /home/circleci/.aws/config
 echo "aws_secret_access_key=$AWS_SECRET_ACCESS_KEY" >> 
 /home/circleci/.aws/config

  eb deploy $BEANSTALK_ENVIRONMENT --profile user --region 
  $BEANSTALK_PRODUCTION_AWS_REGION &&
  echo 'Deployment Succeed' >> /tmp/workspace/beanstalk-deploy- 
  status.txt