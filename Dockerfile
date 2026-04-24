FROM gcc:13

WORKDIR /app

COPY . /app

RUN g++ server.cpp -o server

EXPOSE 8080

CMD ["./server"]