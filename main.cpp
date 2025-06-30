#include "music_app.hpp"
#include <iostream>

int main() {
    loadArtists("artists.txt");
    loadAlbums("albums.txt");
    loadSongs("songs.txt");

    int choice;
    do {
        std::cout << "\n-- Main Menu --\n";
        std::cout << "1. Display Artists\n2. Display Albums\n3. Display Songs\n4. Playlist Menu\n0. Exit\n";
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
