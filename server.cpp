#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "httplib.h"

using namespace std;
using namespace httplib;

class HealthModule {
protected:
    string filename;

public:
    HealthModule(string file) {
        filename = file;
    }

    void appendData(const string& data) {
        ofstream file(filename, ios::app);
        file << data << endl;
        file.close();
    }

    string getAllData() {
        ifstream file(filename);
        string line, all;

        while (getline(file, line)) {
            all += line + "\n";
        }
        return all;
    }
};

class Profile : public HealthModule {
public:
    Profile() : HealthModule("data/profile.txt") {}
};

class Workout : public HealthModule {
public:
    Workout() : HealthModule("data/workout.txt") {}
};

class Food : public HealthModule {
public:
    Food() : HealthModule("data/food.txt") {}
};

class Water : public HealthModule {
public:
    Water() : HealthModule("data/water.txt") {}
};

class Sleep : public HealthModule {
public:
    Sleep() : HealthModule("data/sleep.txt") {}
};

class Steps : public HealthModule {
public:
    Steps() : HealthModule("data/steps.txt") {}
};

class Notes : public HealthModule {
public:
    Notes() : HealthModule("data/notes.txt") {}
};

class Progress : public HealthModule {
public:
    Progress() : HealthModule("data/progress.txt") {}
};

int main() {
    Server svr;

    Profile profile;
    Workout workout;
    Food food;
    Water water;
    Sleep sleep;
    Steps steps;
    Notes notes;
    Progress progress;

    svr.Get("/", [](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Server running", "text/plain");
    });

    svr.Post("/saveProfile", [&](const Request& req, Response& res) {
        profile.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Profile Saved", "text/plain");
    });

    svr.Get("/getProfile", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(profile.getAllData(), "text/plain");
    });

    svr.Post("/addWorkout", [&](const Request& req, Response& res) {
        workout.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Workout Added", "text/plain");
    });

    svr.Get("/getWorkout", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(workout.getAllData(), "text/plain");
    });

    svr.Post("/addFood", [&](const Request& req, Response& res) {
        food.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Food Added", "text/plain");
    });

    svr.Get("/getFood", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(food.getAllData(), "text/plain");
    });

    svr.Post("/updateWater", [&](const Request& req, Response& res) {
        ofstream file("data/water.txt");
        file << req.body;
        file.close();
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Water Updated", "text/plain");
    });

    svr.Get("/getWater", [&](const Request&, Response& res) {
        ifstream file("data/water.txt");
        string data;
        getline(file, data);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(data, "text/plain");
    });

    svr.Post("/addSleep", [&](const Request& req, Response& res) {
        sleep.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Sleep Added", "text/plain");
    });

    svr.Get("/getSleep", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(sleep.getAllData(), "text/plain");
    });

    svr.Post("/updateSteps", [&](const Request& req, Response& res) {
        ofstream file("data/steps.txt");
        file << req.body;
        file.close();
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Steps Updated", "text/plain");
    });

    svr.Get("/getSteps", [&](const Request&, Response& res) {
        ifstream file("data/steps.txt");
        string data;
        getline(file, data);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(data, "text/plain");
    });

    svr.Post("/addNote", [&](const Request& req, Response& res) {
        notes.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Note Added", "text/plain");
    });

    svr.Get("/getNotes", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(notes.getAllData(), "text/plain");
    });

    svr.Post("/addProgress", [&](const Request& req, Response& res) {
        progress.appendData(req.body);
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("Progress Added", "text/plain");
    });

    svr.Get("/getProgress", [&](const Request&, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content(progress.getAllData(), "text/plain");
    });

    int port = 3000;
    if (getenv("PORT")) {
        port = stoi(getenv("PORT"));
    }

    cout << "Server running on port " << port << endl;
    svr.listen("0.0.0.0", port);
}