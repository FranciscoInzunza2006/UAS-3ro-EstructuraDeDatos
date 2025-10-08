import java.util.Random;

public class CpuPlayer extends Player {
    private static final Random random = new Random();

    @Override
    public void init() {
        int placed_ships = 0;
        while (placed_ships < Player.SHIPS_AMOUNT) {
            final Coordinates ship_pos = new Coordinates(random.nextInt(grid.width), random.nextInt(grid.height));
            final boolean vertical = random.nextBoolean();
            int ship_length = placed_ships + 2;
            if (placed_ships > 1) ship_length--;

            if (placeShips(ship_pos, vertical, ship_length))
                placed_ships++;
        }
    }

    @Override
    public boolean turn(Player target) {
        Util.printSection("CPU");

        Coordinates attack_pos = new Coordinates(random.nextInt(target.grid.width), random.nextInt(target.grid.height));
        final boolean result =  attack(target, attack_pos);
        Util.SCANNER.next();

        return result;
    }
}
