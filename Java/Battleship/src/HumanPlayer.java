public class HumanPlayer extends Player {
    @Override
    public void init() {
        for (int placed_ships = 0; placed_ships < SHIPS_AMOUNT; placed_ships++) {
            Util.clearConsole();
            Util.printSection("Coloca tus barcos");
            grid.drawGrid();

            int ship_length = placed_ships + 2;
            if (placed_ships > 1) ship_length--;

            Util.printSection();
            System.out.printf("El siguiente barco tiene una longitud de %d\n", ship_length);

            while (true) {
                System.out.print("¿Colocar de forma vertical (1/0)? ");
                final boolean vertical = Util.SCANNER.nextInt() != 0;

                final Coordinates ship_pos = Coordinates.askUser(grid.width, grid.height);
                if (placeShips(ship_pos, vertical, ship_length))
                    break;

                System.out.println("Una de las casillas se encuentra ocupada o esta fuera de rango.");
            }
        }
        System.out.print("\n".repeat(40));
    }

    @Override
    public boolean turn(Player target) {
        Util.printSection("Tu tablero");
        grid.drawGrid();
        // target.grid.drawGrid();

        Util.printSection("Tablero enemigo (Elije donde atacar)");
        target_grid.drawGrid();

        Coordinates attack_pos = Coordinates.askUser(target_grid.width, target_grid.height);
        boolean result = attack(target, attack_pos);

        Util.printSection();
        Util.SCANNER.next();

        if (!result) {
            System.out.print("\n".repeat(40));
            if (target instanceof HumanPlayer) {
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        return result;
    }
}
