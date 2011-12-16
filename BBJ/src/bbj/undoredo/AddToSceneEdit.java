package bbj.undoredo;

import bbj.*;
import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;
import javax.swing.*;
import javax.swing.undo.*;

/**
 *
 * @author Lemon
 */
public class AddToSceneEdit extends AbstractUndoableEdit {

    private Scene m_scene;
    private SceneItem m_oldValue;
    private String m_describe;

    public AddToSceneEdit(Scene scene, SceneItem value) {
        m_scene = scene;
        m_oldValue = value;

    }

    @Override
    public String getPresentationName() {
        m_describe = "Добавление сущности на сцену";
        return m_describe;
    }

    @Override
    public void undo() throws CannotUndoException {

        super.undo();

        if (m_oldValue.getClass().getSuperclass().getName().equals("UIMessage")){
            m_scene.remove(((UIMessage)m_oldValue).m_focusReceiver);
            m_scene.remove(((UIMessage)m_oldValue).m_focusSender);
            m_scene.getGraphicsObjects().remove(((UIMessage)m_oldValue).m_focusSender);
            m_scene.getGraphicsObjects().remove(((UIMessage)m_oldValue).m_focusReceiver);
        }
        
        m_scene.getGraphicsObjects().remove(m_oldValue);
        m_scene.remove(m_oldValue);
      //  m_scene.getModel().removeObject(m_oldValue
  
        m_scene.repaint();

    }

    @Override
    public void redo() throws CannotUndoException {

        super.redo();
        if (m_oldValue.getClass().getSuperclass().getName().equals("UIMessage")){
           m_scene.add(((UIMessage)m_oldValue).m_focusSender);
           m_scene.add(((UIMessage)m_oldValue).m_focusReceiver);
           m_scene.getGraphicsObjects().add(((UIMessage)m_oldValue).m_focusSender);
           m_scene.getGraphicsObjects().add(((UIMessage)m_oldValue).m_focusReceiver);
        }
        
        m_scene.getGraphicsObjects().add(m_oldValue);
        m_scene.add(m_oldValue);
        m_scene.repaint();
    }
}
