class Battleship {
    private final Player p1;
    private final Player p2;

    public Battleship() {
        Util.clearConsole();
        Util.printSection();
        System.out.print(" (1) Jugador vs Computadora\n (2) Jugador vs Jugador\n");
        Util.printSection();

        final int mode = Util.get_int_range(1, 2);
        if (mode == 1) {
            p1 = new HumanPlayer();
            p2 = new CpuPlayer();
        } else {
            p1 = new HumanPlayer();
            p2 = new HumanPlayer();
        }
    }

    public void loop() {
        int turn = 0;
        Player shooter;
        Player target;
        do {
            Util.clearConsole();
            Util.printSection(String.format("Turno %d", turn + 1));

            shooter = (turn % 2 == 0) ? p1 : p2;
            target = (turn % 2 == 1) ? p1 : p2;

            turn++;
        } while (!shooter.turn(target));
    }
}
