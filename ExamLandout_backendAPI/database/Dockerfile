FROM mysql

WORKDIR /usr/src/app

RUN apt-get update \
    && apt-get install -y vim \
    && apt-get install  -y --allow-unauthenticated mysql-client 

RUN   socket=/run/mysqld/mysqlx.sock
# find / -type s \


COPY *.sql /usr/src/app/

# EXPOSE 9009
