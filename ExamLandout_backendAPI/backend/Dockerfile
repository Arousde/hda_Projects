FROM node:10

WORKDIR /usr/src/app

RUN apt-get update \
    && apt-get install -y vim \
    && apt-get install  -y --allow-unauthenticated mysql-client \
    && apt-get install -y procps
    # && apt-get install -y netcat 

COPY package*.json /usr/src/app/

WORKDIR /usr/src/app

RUN npm install > /usr/src/app/log.txt 2>&1 \
    && npm install mysql \
    && npm install cors \
    && npm install cookie-parser \
    && npm install dotenv \
    && npm install mocha  \
    && npm install chai  \
    && npm install chai-http 
    
## wait tool from github to wait for db befor starting
ADD https://github.com/ufoscout/docker-compose-wait/releases/download/2.2.1/wait /wait
RUN chmod +x /wait

## Launch the wait tool and then your application
CMD /wait && npm test

