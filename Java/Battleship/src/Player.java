public abstract class Player {
    public static final int SHIPS_AMOUNT = 5;
    protected int lives = 0;
    Grid grid;
    Grid target_grid;

    public Player() {
        grid = new Grid(Grid.GRID_WIDTH, Grid.GRID_HEIGHT);
        target_grid = new Grid(Grid.GRID_WIDTH, Grid.GRID_HEIGHT);

        init();
    }

    public abstract void init();

    public abstract boolean turn(Player target);

    public boolean attack(Player enemy, final Coordinates coordinates) {
        final char tile_shoot = enemy.grid.get(coordinates);
        final boolean shoot_result = (tile_shoot == Grid.SHIP);
        final String shoot_message = shoot_result ? "Acierto" : "Fallo";
        final char new_tile = shoot_result ? Grid.FLAG : Grid.SHOOT;

        Util.printSection(shoot_message);
        enemy.grid.set(coordinates, new_tile);
        target_grid.set(coordinates, new_tile);

        boolean enemy_sunk = false;
        if (shoot_result) {
            enemy.lives--;
            if (enemy.lives == 0) {
                Util.printSection("GG");
                enemy_sunk = true;
            }
        }

        return enemy_sunk;
    }

    protected boolean placeShips(final Coordinates ship_pos, final boolean vertical, final int ship_length) {
        if (!vertical) {
            if (ship_pos.x + ship_length > grid.width) return false;

            for (int i = 0; i < ship_length; i++) {
                if (grid.get(ship_pos.x + i, ship_pos.y) != Grid.EMPTY) return false;
            }

            for (int i = 0; i < ship_length; i++) {
                grid.set(ship_pos.x + i, ship_pos.y, Grid.SHIP);
                lives++;
            }
        } else {
            if (ship_pos.y + ship_length > grid.height) return false;

            for (int i = 0; i < ship_length; i++) {
                if (grid.get(ship_pos.x, ship_pos.y + i) != Grid.EMPTY) return false;
            }

            for (int i = 0; i < ship_length; i++) {
                grid.set(ship_pos.x, ship_pos.y + i, Grid.SHIP);
                lives++;
            }
        }

        return true;
    }
}
