public class Tickets {
    record Person(String name, int duration) {
    }

    static String[] name = {
            "abe",
            "amy",
            "cal",
            "carrie",
            "terry",
            "berry",
            "sherry",
            "ben",
            "jen",
            "ken",
    };

    static final Object door = new Object();
    static int club_count = 0;
    static final int club_limit = 2;

    static void enterClub(Person p) throws InterruptedException {
        synchronized (door) {
            // pthread_mutex_lock(&door);
            // pthread_cond_wait(&cond);
            while (club_count >= club_limit) door.wait();
            club_count++;
            // pthread_mutex_unlock(&door);
        }
        System.out.printf("%s entered club\n", p.name);
        Thread.sleep(p.duration * 1000 );
        System.out.printf("%s left club after %d seconds\n", p.name, p.duration);
        synchronized (door) {
            // pthread_mutex_lock(&door);
            club_count--;
            door.notifyAll();
            // pthread_cond_signal(&cond);
            // pthread_mutex_unlock(&door);
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] ph = new Thread[10];
        Person[] people = new Person[10];

        // pthread_mutex_init(&door, NULL);
        //pthread_cond_init(&bell, NULL);
        for (int i = 0; i < 10; i++) {
            people[i] = new Person(name[i], 5 + (i % 2));
        }

        for (int i = 0; i < 10; i++) {
            final int personNumber = i;
            ph[i] = new Thread(() -> {
                try {
                    enterClub(people[personNumber]);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
            ph[i].start();
        }

        for (int i = 0; i < 10; i++) {
            ph[i].join();
        }
    }
}
