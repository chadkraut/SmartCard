import javax.swing.*;


class NoCardPopUp {
    private JPanel NoCard;
    private JLabel NoCardLabael;

    void buildCardPopUp() {
        JFrame frame3 = new JFrame("No Card Detected!");
        frame3.setContentPane(new NoCardPopUp().NoCard);
        frame3.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame3.pack();
        frame3.setLocationRelativeTo(null);
        frame3.setVisible(true);
    }
}
