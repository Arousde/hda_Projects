FROM node:10

WORKDIR /usr/src/app/ELOapp

RUN apt-get update \
    && apt-get install -y vim \
    && npm install -g @angular/cli

COPY ELOapp/package*.json /usr/src/app/ELOapp/

WORKDIR /usr/src/app/ELOapp

# RUN npm install > /usr/src/app/log.txt 2>&1
RUN npm ci > /usr/src/app/log.txt 2>&1

CMD [ "ng", "serve", "--host", "0.0.0.0"]








