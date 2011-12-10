/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

/**
 *
 * @author Alexander
 */
public class UIDestroyMessage extends UIMessage {

    /** Номер экзампляра данного класса на сцене */
    public static int m_localNumber = 0;
    
    @Override
    protected void setDefaultName() {
        m_text = "Сообщение " + Integer.toString(m_localNumber++);
    }
    
}
