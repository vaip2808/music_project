// music_streaming_app.cpp
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>

class Entity {
public:
    virtual std::string getId() const = 0;
};

class Song;

class Artist : public Entity {
public:
    std::string id, name, genre;
    std::set<std::string> songIds;
    std::string getId() const override { return id; }
};

class Album : public Entity {
public:
    std::string id, title;
    int releaseYear;
    std::vector<std::string> songIds;
    std::string getId() const override { return id; }
};

class Song : public Entity {
public:
    std::string id, title, albumId;
    int duration;
    std::vector<std::string> artistIds;
    std::string getId() const override { return id; }
};

class Playlist : public Entity {
public:
    std::string id, name;
    std::vector<std::string> songIds;
    std::string getId() const override { return id; }
};

// Repositories
std::map<std::string, Song> songs;
std::map<std::string, Album> albums;
std::map<std::string, Artist> artists;
std::map<std::string, Playlist> playlists;

void loadArtists(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || (!isdigit(line[0]) && line[0] != '-')) continue;
        std::istringstream ss(line);
        Artist artist;
        std::getline(ss, artist.id, ',');
        std::getline(ss, artist.name, ',');
        std::getline(ss, artist.genre);
        artists[artist.id] = artist;
    }
}

void loadAlbums(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || (!isdigit(line[0]) && line[0] != '-')) continue;
        std::istringstream ss(line);
        Album album;
        std::string year;
        std::getline(ss, album.id, ',');
        std::getline(ss, album.title, ',');
        std::getline(ss, year);
        try {
            album.releaseYear = std::stoi(year);
        } catch (...) {
            std::cerr << "⚠️ Invalid release year in: " << line << "";
            continue;
        }
        albums[album.id] = album;
    }
}

void loadSongs(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << "";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || (!isdigit(line[0]) && line[0] != '-')) continue;

        std::istringstream ss(line);
        Song song;
        std::string duration;
        std::getline(ss, song.id, ',');
        std::getline(ss, song.title, ',');
        std::getline(ss, duration, ',');
        std::getline(ss, song.albumId, ',');

        std::string artistId;
        while (std::getline(ss, artistId, ';')) {
            if (!artistId.empty()) {
                song.artistIds.push_back(artistId);
                if (artists.count(artistId)) {
                    artists[artistId].songIds.insert(song.id);
                } else {
                    std::cerr << "⚠️ Warning: Artist ID not found: " << artistId << "";
                }
            }
        }

        try {
            song.duration = std::stoi(duration);
        } catch (...) {
            std::cerr << "⚠️ Invalid duration in: " << line << "";
            continue;
        }

        if (!albums.count(song.albumId)) {
            std::cerr << "⚠️ Warning: Album ID not found: " << song.albumId << "";
            continue;
        }

        songs[song.id] = song;
        albums[song.albumId].songIds.push_back(song.id);
    }
}

void displayAllArtists() {
    for (const auto& [id, artist] : artists) {
        if (artist.name.empty()) continue;
        std::cout << artist.name << " (" << artist.genre << ")";
    }
}

void displayAllAlbums() {
    for (const auto& [id, album] : albums) {
        if (album.title.empty()) continue;
        std::cout << album.title << " (" << album.releaseYear << ")";
    }
}

void displayAllSongs() {
    for (const auto& [id, song] : songs) {
        if (song.title.empty()) continue;
        std::cout << song.title << " (" << song.duration << "s)";
    }
}

void createPlaylist() {
    Playlist p;
    std::cout << "Enter playlist ID: "; std::cin >> p.id;
    std::cout << "Enter playlist name: "; std::cin.ignore(); std::getline(std::cin, p.name);
    playlists[p.id] = p;
    std::cout << "Playlist created.";
}

void updatePlaylist() {
    std::string id;
    std::cout << "Enter playlist ID to update: "; std::cin >> id;
    if (playlists.count(id)) {
        std::cout << "Enter new name: "; std::cin.ignore(); std::getline(std::cin, playlists[id].name);
        std::cout << "Playlist updated.";
    } else {
        std::cout << "Playlist not found.";
    }
}

void deletePlaylist() {
    std::string id;
    std::cout << "Enter playlist ID to delete: "; std::cin >> id;
    if (playlists.erase(id)) {
        std::cout << "Playlist deleted.";
    } else {
        std::cout << "Playlist not found.";
    }
}

void listPlaylists() {
    for (const auto& [id, p] : playlists) {
        std::cout << "Playlist: " << p.name << " [" << id << "]";
    }
}

void playlistMenu() {
    int choice;
    do {
        std::cout << "\n-- Playlist Menu --";
        std::cout << "\n1. Create Playlist";
        std::cout << "\n2. Update Playlist";
        std::cout << "\n3. Delete Playlist";
        std::cout << "\n4. List Playlists";
        std::cout << "\n0. Back";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: createPlaylist(); break;
            case 2: updatePlaylist(); break;
            case 3: deletePlaylist(); break;
            case 4: listPlaylists(); break;
        }
    } while (choice != 0);
}

int main() {
    loadArtists("artists.txt");
    loadAlbums("albums.txt");
    loadSongs("songs.txt");

    int choice;
    do {
        std::cout << "-- Main Menu --";
        std::cout << "\n1. Display Artists";
        std::cout << "\n2. Display Albums";
        std::cout << "\n3. Display Songs";
        std::cout << "\n4. Playlist Menu";
        std::cout << "\n0. Exit";
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1: displayAllArtists(); break;
            case 2: displayAllAlbums(); break;
            case 3: displayAllSongs(); break;
            case 4: playlistMenu(); break;
        }
    } while (choice != 0);

    return 0;
}
