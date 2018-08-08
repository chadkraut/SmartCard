
import sun.security.pkcs11.SunPKCS11;
import sun.security.pkcs11.wrapper.PKCS11;
import sun.security.pkcs11.wrapper.PKCS11Exception;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.ProviderException;
import java.security.Security;


class CardReader {
    private String DLL;
    private KeyStore.Builder builder;
    private char[] PIN;
    private SunPKCS11 prov;
    private NoCardPopUp noCardgui = new NoCardPopUp();
    private String p;


    /**
     * Checks if there is are tokens in slots then builds a GUI if not.
     */
    void checkInserted() {
        PKCS11 pkcs11 = null;
        long[] slots = {};
        try {
            pkcs11 = PKCS11.getInstance(p, "C_GetFunctionList", null, false);
            slots = pkcs11.C_GetSlotList(true);
            if (slots.length < 1)
                noCardgui.buildCardPopUp();
        } catch (IOException | PKCS11Exception e) {
            e.printStackTrace();
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
        p = path;
        DLL = "library = " + p + "\n";
    }

    /**
     * Sets the user's PIN to the char[] entered in GUI.
     */
    void setPin(char[] myPIN) {
        PIN = myPIN;
    }

    /**
     * Creates the config file using proper DLL path then converts file to a byte stream
     * for the provider to use.
     */
    void setProvider() {
        String config = "name = SmartCard\n" +
                getDLL() +
                "slotListIndex = 0";
        ByteArrayInputStream confStream = new ByteArrayInputStream(config.getBytes());
        prov = new SunPKCS11(confStream);
        Security.addProvider(prov);
    }

    /**
     * Returns the provider.
     *
     * @return SunPKCS11 Provider
     */
    private SunPKCS11 getProvider() {
        return prov;
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
    }
}
