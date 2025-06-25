FROM ubuntu

RUN apt-get update && apt-get install -y apache2

ENV first_var=hello-world

RUN echo "$first_var" > /var/www/html/test.html

RUN echo "$(whoami)" > /var/www/html/test.html

RUN useradd -m jr

USER jr

RUN echo "$(whoami)" > /tmp/user2.html

USER root

RUN cp /tmp/user2.html /var/www/html

CMD ["apache2ctl", "-D", "FOREGROUND"]
