import javax.smartcardio.CardException;
import javax.smartcardio.CardTerminal;
import javax.smartcardio.CardTerminals;
import javax.smartcardio.TerminalFactory;
import java.io.*;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.Provider;
import java.security.Security;


class CardReader {
    private String DLL;
    private KeyStore.Builder builder;
    private char[] PIN;
    private NoCardPopUp noCardgui = new NoCardPopUp();
    private Provider provi;

    /**
     * Checks if there is are tokens in slots then builds a GUI if not.
     */
    void checkInserted() {
        CardTerminals cardTerminals = TerminalFactory.getDefault().terminals();
        try {
            CardTerminal terminal = cardTerminals.list().get(0);
            if (!terminal.isCardPresent()) {
                noCardgui.buildCardPopUp();
            }
        } catch (CardException e) {
            e.printStackTrace();
            System.out.println("Is reader connected?");
        }
    }

    /**
     * Gets the DLL.
     *
     * @return String DLL
     */
    private String getDLL() {
        return DLL;
    }

    /**
     * Sets the DLL path from user input to the library config field.
     */
    void setLibrary(String path) {
        DLL = "library = " + path + "\n";
    }

    /**
     * Sets the user's PIN to the char[] entered in GUI.
     */
    void setPin(char[] myPIN) {
        PIN = myPIN;
    }

    /**
     * Creates the config file using proper DLL path.
     */
    void makeConfig() {
        String config2 = "name = SmartCard\n" +
                getDLL() +
                "slotListIndex = 0";
        try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream("pkcs11config.cfg"), "utf-8"))) {
            writer.write(config2);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Loads the provider.
     */
    void loadProvider() {
        provi = Security.getProvider("SunPKCS11");
        provi = provi.configure("pkcs11config.cfg");
        Security.addProvider(provi);
    }

    /**
     * Returns the provider.
     *
     * @return Provider
     */
    private Provider getProvider() {
        return provi;
    }

    /**
     * Uses Keystore Builder to build a new instance for the provider.
     */
    void buildKeyStore() {
        builder = KeyStore.Builder.newInstance("PKCS11", getProvider(), new KeyStore.PasswordProtection(PIN));
    }

    /**
     * Gets the KeyStore that was built by builder.
     *
     * @return KeyStore
     * @throws KeyStoreException if build fails
     */
    KeyStore getKeyStore() throws KeyStoreException {
        return builder.getKeyStore();
    }

    /**
     * Removes provider from Keystore.
     */
    void cleanUp() {
        Security.removeProvider("SunPKCS11-SmartCard");
        PIN = null;
        File file = new File("pkcs11config.cfg");
        file.deleteOnExit();
    }
}
