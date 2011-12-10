
package bbj.undoredo;

import bbj.graphicsobjects.*;
import bbj.virtualobjects.*;

import java.awt.*;
import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotUndoException;
import java.util.*;

/**
 *
 * @author Lemon
 */
public class ClearSceneEdit extends AbstractUndoableEdit {

    private Scene m_scene;
    private ArrayList<SceneItem> m_objects;
    private VirtualModel m_model;
    private String m_describe;

  

    public ClearSceneEdit(Scene scene) {
        m_scene = scene;
        m_objects = (ArrayList<SceneItem>)scene.getGraphicsObjects().clone();
        m_model = new VirtualModel(scene);

    }

    @Override
    public String getPresentationName() {
        m_describe = "Очистка сцены";
        return m_describe;
    }

    @Override
    public void undo() throws CannotUndoException {

        super.undo();
        
        m_scene.setVirtualModel(m_model);
        m_scene.setGraphicsObjects(m_objects);
        m_scene.repaint();

    }

    @Override
    public void redo() throws CannotUndoException {

        super.redo();

        m_scene.clear();
        m_scene.repaint();
    }
}
